---
layout: page
title: The Philosopher King 
tagline: CSE 167 Final Project
---
{% include JB/setup %}

<!-- TODO add a welcome thingy -->


<div class="posts">
  {% for post in site.posts %}
    <h3 style="border-bottom: 1px solid #eee;"><a style="color:#444;" href="{{ BASE_PATH}}{{ post.url }}">{{post.title}}</a> <small>{{ post.tagline }}</small></h3>
    <p style="margin-top: -10px;"><em>{{ post.date | date_to_string }}</em></p>
    <p>{{ post.content }}</p>
  {% endfor %}
</div>
