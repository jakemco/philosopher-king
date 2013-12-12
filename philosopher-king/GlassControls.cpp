#include "GlassControls.h"
#include "Vector4.h"
#include "Matrix4.h"

#ifdef WIN32

#include <initguid.h>

#define CXN_SUCCESS                       0
#define CXN_ERROR                         1
#define CXN_MAX_INQUIRY_RETRY             3
#define CXN_DELAY_NEXT_INQUIRY            15
#define MAX_CONNECTION_CYCLES 1

#define READ_BT_BUFFER_SIZE 1024

ULONG NameToBthAddr(_In_ const LPWSTR pszRemoteName, _Out_ PSOCKADDR_BTH pRemoteBthAddr);

#endif

#define PITCH_ROLL_FRAME_ID 9001
#define FRAME_SIZE 12
#define FRAME_ID_SIZE 4
#define PITCH_OFFSET 1
#define ROLL_OFFSET 2

#define FIRIN_MAH_LASER_FRAME_ID 42
#define LASER_VALUE_OFFSET 1

#define TOGGLE_TARGETING_FRAME_ID 1337

// During normal wearing of glass, it points up a little bit. Correct for that.
#define PITCH_CORRECTION 0.164

// The guid of the bt service
// a2b6fe70-614b-11e3-949a-0800200c9a66
#ifdef WIN32
DEFINE_GUID(g_guidServiceClass, 0xa2b6fe70, 0x614b, 0x11e3, 0x94, 0x9a, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66);
#endif

#define GLASS_NAME L"Zach Johnson's Glass"

GlassControls::GlassControls() {
	this->pitch = 0;
	this->pitchZero = PITCH_CORRECTION;
	this->roll = 0;
	this->btReadThread = nullptr;
	this->fireLasers = false;
	this->shouldToggleTargetingValue = false;
}


GlassControls::~GlassControls() {
}

void GlassControls::connectToGlass() {
#ifdef WIN32
	this->btReadThread = new std::thread(&GlassControls::initiateBluetooth, this);
#else
	// not supported
#endif
}

void GlassControls::initiateBluetooth() {
#ifdef WIN32
	ULONG       ulRetCode = CXN_SUCCESS;
	WSADATA     WSAData = { 0 };
	SOCKADDR_BTH RemoteBthAddr = { 0 };

	// Start up winsock
	ulRetCode = WSAStartup(MAKEWORD(2, 2), &WSAData);
	if (CXN_SUCCESS != ulRetCode) {
		wprintf(L"-FATAL- | Unable to initialize Winsock version 2.2\n");
		return;
	}

	// Ask for the Glass device
	ulRetCode = NameToBthAddr(GLASS_NAME, &RemoteBthAddr);
	if (CXN_SUCCESS != ulRetCode) {
		wprintf(L"-FATAL- | Unable to get address of the remote radio having name %s\n", GLASS_NAME);
		return;
	}

	this->bluetoothLoop(RemoteBthAddr);

#endif
}

void GlassControls::calibratePitch() {
	this->pitchZero = -this->pitch;
}

float GlassControls::getPitch() {
	return this->pitch + this->pitchZero;
}

float GlassControls::getRoll() {
	return this->roll;
}

bool GlassControls::getLasersFired() {
	return this->fireLasers;
}

void GlassControls::resetLasers() {
	this->fireLasers = false;
}


bool GlassControls::shouldToggleTargeting() {
	return this->shouldToggleTargetingValue;
}

void GlassControls::resetToggleTargeting() {
	this->shouldToggleTargetingValue = false;
}

float GlassControls::getInterpolatedY() {
	Vector4 vector = Matrix4::rotateX(this->getPitch() + 3.14 / 2).multiply(Vector4(0, 5, 0));
	return (float)vector.y();
}

float GlassControls::getInterpolatedX() {
	Vector4 vector = Matrix4::rotateZ(-this->getRoll()).multiply(Vector4(0, 3, 0));
	return (float)vector.x();
}

#ifdef WIN32

ULONG GlassControls::bluetoothLoop(SOCKADDR_BTH remoteAddr) {
	ULONG ulRetCode = CXN_SUCCESS;
	SOCKADDR_BTH sockAddrBthServer = remoteAddr;

	// Setting address family to AF_BTH indicates winsock2 to use Bluetooth sockets
	// Port should be set to 0 since ServiceClassId is spesified.
	sockAddrBthServer.addressFamily = AF_BTH;
	sockAddrBthServer.serviceClassId = g_guidServiceClass;
	sockAddrBthServer.port = 0;
	
	for (int connectionAttempt = 0;
		0 == ulRetCode && connectionAttempt < MAX_CONNECTION_CYCLES;
		connectionAttempt++) {

		// Open a bluetooth socket using the RFCOMM protocol
		SOCKET localSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
		if (localSocket == INVALID_SOCKET) {
			wprintf(L"=CRITICAL= | socket() call failed. WSAGetLastError = [%d]\n", WSAGetLastError());
			return CXN_ERROR;
		}

		// Connect to the remote service on the Glass device
		if (SOCKET_ERROR ==	
			connect(
				localSocket,
				(struct sockaddr *) &sockAddrBthServer,
				sizeof(SOCKADDR_BTH)
			)) {
				wprintf(L"=CRITICAL= | connect() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
				return CXN_ERROR;
		}

		printf("Connected to Glass\n");

		// Start reading from the socket
		char incomingData[READ_BT_BUFFER_SIZE];
		char * incomingDataPtr = incomingData;
		int lengthReceived = 0;
		int length = 0;
		bool gotPacketsBefore = false;

		do {
			lengthReceived = recv(
				localSocket,
				incomingDataPtr,
				READ_BT_BUFFER_SIZE - length,
				0);

			if (lengthReceived == SOCKET_ERROR) {
				wprintf(L"=CRITICAL= | recv() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
				return CXN_ERROR;
			}

			if (!gotPacketsBefore) {
				gotPacketsBefore = true;
				printf("Getting packets from Glass\n");
			}

			// Swap the endianness of the bytes read.
			// Begin at the last divisible by 4 boundary.
			// End at the last divisible by 4 boundary.
			int beginEndianSwap = (length / 4) * 4;
			int endEndianSwap = ((length + lengthReceived) / 4) * 4;
			for (int i = beginEndianSwap; i < endEndianSwap; i += 4) {
				int tmp = incomingData[i];
				incomingData[i] = incomingData[i + 3];
				incomingData[i + 3] = tmp;

				tmp = incomingData[i + 1];
				incomingData[i + 1] = incomingData[i + 2];
				incomingData[i + 2] = tmp;
			}

			length += lengthReceived;
			incomingDataPtr += lengthReceived;

			int readPos = 0;
			for (; readPos < length - FRAME_SIZE; readPos += FRAME_ID_SIZE) {
				int frameId = ((int *)incomingData)[readPos];
				if (frameId == PITCH_ROLL_FRAME_ID) {
					this->pitch = ((float *)incomingData)[readPos + PITCH_OFFSET];
					this->roll = ((float *)incomingData)[readPos + ROLL_OFFSET];

					//printf("got frame: pitch: %f, roll %f\n", pitch, roll);
				}
				else if (frameId == FIRIN_MAH_LASER_FRAME_ID) {
					int value = ((int *)incomingData)[readPos + LASER_VALUE_OFFSET];
					if (value) {
						this->fireLasers = true;
					}

					//printf("got laser frame: value: %d\n", value);
				}
				else if (frameId == TOGGLE_TARGETING_FRAME_ID) {
					this->shouldToggleTargetingValue = true;
					//printf("got toggle frame\n");
				}
			}

			// If we did eat data, shift everything back to re-normalize the stream
			if (readPos > 0) {
				incomingDataPtr -= readPos;
				int newLength = length - readPos;
				int writePos = 0;
				for (; readPos < length; readPos++, writePos++) {
					incomingData[writePos] = incomingData[readPos];
				}

				length = newLength;
			}
		} while (lengthReceived > 0);

		if (SOCKET_ERROR == closesocket(localSocket)) {
			wprintf(L"=CRITICAL= | closesocket() call failed w/socket = [0x%I64X]. WSAGetLastError=[%d]\n", (ULONG64)localSocket, WSAGetLastError());
			return CXN_ERROR;
		}

		localSocket = INVALID_SOCKET;
	}

	return CXN_SUCCESS;
}

// WINSOCK DARK MAGIC BELOW
// TODO clean up style

//
// NameToBthAddr converts a bluetooth device name to a bluetooth address,
// if required by performing inquiry with remote name requests.
// This function demonstrates device inquiry, with optional LUP flags.
//
ULONG NameToBthAddr(_In_ const LPWSTR pszRemoteName, _Out_ PSOCKADDR_BTH pRemoteBtAddr)
{
	INT             iResult = CXN_SUCCESS;
	BOOL            bContinueLookup = FALSE, bRemoteDeviceFound = FALSE;
	ULONG           ulFlags = 0, ulPQSSize = sizeof(WSAQUERYSET);
	HANDLE          hLookup = NULL;
	PWSAQUERYSET    pWSAQuerySet = NULL;

	ZeroMemory(pRemoteBtAddr, sizeof(*pRemoteBtAddr));

	pWSAQuerySet = (PWSAQUERYSET)HeapAlloc(GetProcessHeap(),
		HEAP_ZERO_MEMORY,
		ulPQSSize);
	if (NULL == pWSAQuerySet) {
		iResult = STATUS_NO_MEMORY;
		wprintf(L"!ERROR! | Unable to allocate memory for WSAQUERYSET\n");
	}

	//
	// Search for the device with the correct name
	//
	if (CXN_SUCCESS == iResult) {

		for (INT iRetryCount = 0;
			!bRemoteDeviceFound && (iRetryCount < CXN_MAX_INQUIRY_RETRY);
			iRetryCount++) {
				//
				// WSALookupService is used for both service search and device inquiry
				// LUP_CONTAINERS is the flag which signals that we're doing a device inquiry.
				//
				ulFlags = LUP_CONTAINERS;

				//
				// Friendly device name (if available) will be returned in lpszServiceInstanceName
				//
				ulFlags |= LUP_RETURN_NAME;

				//
				// BTH_ADDR will be returned in lpcsaBuffer member of WSAQUERYSET
				//
				ulFlags |= LUP_RETURN_ADDR;

				if (0 == iRetryCount) {
					wprintf(L"*INFO* | Inquiring device from cache...\n");
				}
				else {
					//
					// Flush the device cache for all inquiries, except for the first inquiry
					//
					// By setting LUP_FLUSHCACHE flag, we're asking the lookup service to do
					// a fresh lookup instead of pulling the information from device cache.
					//
					ulFlags |= LUP_FLUSHCACHE;

					//
					// Pause for some time before all the inquiries after the first inquiry
					//
					// Remote Name requests will arrive after device inquiry has
					// completed.  Without a window to receive IN_RANGE notifications,
					// we don't have a direct mechanism to determine when remote
					// name requests have completed.
					//
					wprintf(L"*INFO* | Unable to find device.  Waiting for %d seconds before re-inquiry...\n", CXN_DELAY_NEXT_INQUIRY);
					Sleep(CXN_DELAY_NEXT_INQUIRY * 1000);

					wprintf(L"*INFO* | Inquiring device ...\n");
				}

				//
				// Start the lookup service
				//
				iResult = CXN_SUCCESS;
				hLookup = 0;
				bContinueLookup = FALSE;
				ZeroMemory(pWSAQuerySet, ulPQSSize);
				pWSAQuerySet->dwNameSpace = NS_BTH;
				pWSAQuerySet->dwSize = sizeof(WSAQUERYSET);
				iResult = WSALookupServiceBegin(pWSAQuerySet, ulFlags, &hLookup);

				//
				// Even if we have an error, we want to continue until we
				// reach the CXN_MAX_INQUIRY_RETRY
				//
				if ((NO_ERROR == iResult) && (NULL != hLookup)) {
					bContinueLookup = TRUE;
				}
				else if (0 < iRetryCount) {
					wprintf(L"=CRITICAL= | WSALookupServiceBegin() failed with error code %d, WSAGetLastError = %d\n", iResult, WSAGetLastError());
					break;
				}

				while (bContinueLookup) {
					//
					// Get information about next bluetooth device
					//
					// Note you may pass the same WSAQUERYSET from LookupBegin
					// as long as you don't need to modify any of the pointer
					// members of the structure, etc.
					//
					// ZeroMemory(pWSAQuerySet, ulPQSSize);
					// pWSAQuerySet->dwNameSpace = NS_BTH;
					// pWSAQuerySet->dwSize = sizeof(WSAQUERYSET);
					if (NO_ERROR == WSALookupServiceNext(hLookup,
						ulFlags,
						&ulPQSSize,
						pWSAQuerySet)) {

							//
							// Compare the name to see if this is the device we are looking for.
							//
							if ((pWSAQuerySet->lpszServiceInstanceName != NULL) &&
								(CXN_SUCCESS == _wcsicmp(pWSAQuerySet->lpszServiceInstanceName, pszRemoteName))) {
									//
									// Found a remote bluetooth device with matching name.
									// Get the address of the device and exit the lookup.
									//
									CopyMemory(pRemoteBtAddr,
										(PSOCKADDR_BTH)pWSAQuerySet->lpcsaBuffer->RemoteAddr.lpSockaddr,
										sizeof(*pRemoteBtAddr));
									bRemoteDeviceFound = TRUE;
									bContinueLookup = FALSE;
							}
					}
					else {
						iResult = WSAGetLastError();
						if (WSA_E_NO_MORE == iResult) { //No more data
							//
							// No more devices found.  Exit the lookup.
							//
							bContinueLookup = FALSE;
						}
						else if (WSAEFAULT == iResult) {
							//
							// The buffer for QUERYSET was insufficient.
							// In such case 3rd parameter "ulPQSSize" of function "WSALookupServiceNext()" receives
							// the required size.  So we can use this parameter to reallocate memory for QUERYSET.
							//
							HeapFree(GetProcessHeap(), 0, pWSAQuerySet);
							pWSAQuerySet = (PWSAQUERYSET)HeapAlloc(GetProcessHeap(),
								HEAP_ZERO_MEMORY,
								ulPQSSize);
							if (NULL == pWSAQuerySet) {
								wprintf(L"!ERROR! | Unable to allocate memory for WSAQERYSET\n");
								iResult = STATUS_NO_MEMORY;
								bContinueLookup = FALSE;
							}
						}
						else {
							wprintf(L"=CRITICAL= | WSALookupServiceNext() failed with error code %d\n", iResult);
							bContinueLookup = FALSE;
						}
					}
				}

				//
				// End the lookup service
				//
				WSALookupServiceEnd(hLookup);

				if (STATUS_NO_MEMORY == iResult) {
					break;
				}
		}
	}

	if (NULL != pWSAQuerySet) {
		HeapFree(GetProcessHeap(), 0, pWSAQuerySet);
		pWSAQuerySet = NULL;
	}

	if (bRemoteDeviceFound) {
		iResult = CXN_SUCCESS;
	}
	else {
		iResult = CXN_ERROR;
	}

	return iResult;
}

#endif
