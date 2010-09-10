TESTS = \
	test_case_050.sh \
	test_case_060.sh \
	test_case_110.sh \
	test_case_130.sh \
	test_case_140.sh \
	test_case_143.sh \
	test_case_145.sh \
	test_case_160.sh \
	test_case_200.sh \
	test_case_210.sh \
	test_case_900.sh \
	unique_slug_01.sh \
	unique_slug_02.sh \
	unique_slug_03.sh \
	unique_slug_04.sh \
	unique_slug_05.sh \
	url_decode_01.sh \
	url_decode_02.sh \
	url_decode_03.sh \
	url_decode_04.sh

check_PROGRAMS = \
	uniqueslug \
	urldecode

CLEANFILES = $(TESTS) \
	out.txt \
	uniqueslug \
	urldecode

TESTS_REDIS_HOST=@tests_redis_host@
TESTS_REDIS_PORT=@tests_redis_port@
TESTS_REDIS_DB_INDEX=@tests_redis_db_index@

uniqueslug_LDADD = ../src/libcore.a
uniqueslug_CPPFLAGS = -I$(top_srcdir)/src
urldecode_LDADD = ../src/libcore.a
urldecode_CPPFLAGS = -I$(top_srcdir)/src

# Note: a test returning 77 is considered 'skipped'
DATA_TEST_INIT = \
	echo "pgrep redis-server >/dev/null || exit 77" >> $@ \
	&& echo "redis-cli -h $(TESTS_REDIS_HOST) -p $(TESTS_REDIS_PORT) -n $(TESTS_REDIS_DB_INDEX) FLUSHDB >/dev/null" >> $@

COMMON_ECHO = \
	echo "TODO_TESTS=anyvalue" >> $@ \
	&& echo "export TODO_TESTS" >> $@ \
	&& echo 'CONTENT_LENGTH=$${\#REQUEST_BODY}' >> $@ \
	&& echo "export CONTENT_LENGTH" >> $@ \
	&& echo "export CONTENT_TYPE" >> $@ \
	&& echo "export REQUEST_URI" >> $@ \
	&& echo "export REQUEST_METHOD" >> $@ \
	&& echo 'echo $${REQUEST_BODY} | ../src/todoservice >out.txt' >> $@
	
COMMON_POST_ECHO = \
	echo "rm -f out.txt" >> $@ \
	&& chmod +x $@


test_case_050.sh:
	echo "REQUEST_URI=/version" >> $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"major\\\">1<\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"minor\\\">0<\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"age\\\">0<\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_060.sh:
	echo "REQUEST_URI=/version" > $@
	echo "REQUEST_METHOD=PUT" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 405 Method Not Allowed\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_110.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "REQUEST_URI=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo 'echo $${REQUEST_BODY} | ../src/todoservice >/dev/null' >> $@ # Second post, identical content
	echo 'echo $${REQUEST_BODY} | ../src/todoservice >/dev/null' >> $@ # Third post, identical content
	echo "REQUEST_METHOD=GET" >> $@ # Now get /todos
	echo '../src/todoservice >out.txt' >> $@
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/todos/my\\\"\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/todos/my-test\\\"\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/todos/my-test-message\\\"\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_130.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "REQUEST_URI=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Location: /todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/todos/my\\\"\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_140.sh:
	echo "REQUEST_BODY=data=My+t%65st%2" > $@
	echo "REQUEST_URI=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 400 Bad Request\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_143.sh:
	echo "REQUEST_BODY=data=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" > $@
	echo "REQUEST_URI=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 413 Request Entity Too Large\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_145.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "REQUEST_URI=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/dogs" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 415 Unsupported Media Type\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_160.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "REQUEST_URI=/todos" >> $@
	echo "REQUEST_METHOD=PUT" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 405 Method Not Allowed\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_200.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "REQUEST_URI=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "REQUEST_URI=/todos/my" >> $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_210.sh:
	echo "REQUEST_URI=/todos/hey" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 404 File Not Found\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_900.sh:
	echo "REQUEST_URI=/dogs" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 404 File Not Found\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

unique_slug_01.sh: uniqueslug
	echo "./uniqueslug dog dog || exit 1" > $@
	$(COMMON_POST_ECHO)

unique_slug_02.sh: uniqueslug
	echo "./uniqueslug dog dog-2 dog || exit 1" > $@
	$(COMMON_POST_ECHO)

unique_slug_03.sh: uniqueslug
	echo "./uniqueslug \"TwO WoRdS\" two || exit 1" > $@
	$(COMMON_POST_ECHO)

unique_slug_04.sh: uniqueslug
	echo "./uniqueslug \"TwO WoRdS\" two-words two || exit 1" > $@
	$(COMMON_POST_ECHO)

unique_slug_05.sh: uniqueslug
	echo "./uniqueslug dog dog-10 dog dog-1 dog-2 dog-3 dog-4 dog-5 dog-6 dog-7 dog-8 dog-9 || exit 1" > $@
	$(COMMON_POST_ECHO)


url_decode_01.sh: urldecode
	echo "./urldecode \"h%65%6C%6co\" hello || exit 1" > $@
	$(COMMON_POST_ECHO)

url_decode_02.sh: urldecode
	echo "./urldecode \"http://dog?q=%63%61%6D%6f\" \"http://dog?q=camo\" || exit 1" > $@
	$(COMMON_POST_ECHO)

url_decode_03.sh: urldecode
	echo "./urldecode \"h%65%6C%6\" hello" > $@ # invalid input, expect failure
	$(COMMON_POST_ECHO)

url_decode_04.sh: urldecode
	echo "./urldecode \"hel%6co+sir+\" \"hello sir \" || exit 1" > $@
	$(COMMON_POST_ECHO)





