#include "BoundingBox.h"


BoundingBox::BoundingBox(const Vector4& p, float width, float height, float depth)
{
	this->min = Vector4(p.x() - width / 2, p.y() - height / 2, p.z() - depth / 2, 1);
	this->max = Vector4(p.x() + width / 2, p.y() + height / 2, p.z() + depth / 2, 1);
}


BoundingBox::~BoundingBox()
{
}

bool BoundingBox::contains(const Vector4& p) const {
	if (p.x() < min.x() || p.x() > max.x()) return false;
	if (p.y() < min.y() || p.y() > max.y()) return false;
	if (p.z() < min.z() || p.z() > max.z()) return false;

	return true;
}

bool BoundingBox::contains(const BoundingBox& b) const {
	if (b.contains(max)) return true;
	if (b.contains(min)) return true;
	if (this->contains(b.max)) return true;
	if (this->contains(b.min)) return true;

	return false;
}

bool BoundingBox::custom(std::function<bool(const Vector4&, const Vector4&)> f) const {
	return f(min,max);
}
