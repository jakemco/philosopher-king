---
layout: page
title: Team Jazz 
tagline: We Improvise All The Things
---
{% include JB/setup %}

<!-- TODO add a welcome thingy -->
Welcome to the blog for Team Jazz's CSE 167 Final Project. Team Jazz is Zach
Johnson, Jacob Maskiewicz, and Amy Chandler. For more about us, see the
[team](team.html) page.

<div class="posts">
  {% for post in site.posts %}
    <h2 style="border-bottom: 1px solid #eee;"><a style="color:#444;" href="{{ BASE_PATH}}{{ post.url }}">{{post.title}}</a> <small>{{ post.tagline }}</small></h2>
    <p style="margin-top: -10px;"><em>{{ post.date | date_to_string }}</em></p>
    <p>{{ post.content }}</p>
  {% endfor %}
</div>
