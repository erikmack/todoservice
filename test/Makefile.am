TESTS = \
	test_case_010.sh \
	test_case_013.sh \
	test_case_016.sh \
	test_case_020.sh \
	test_case_050.sh \
	test_case_053.sh \
	test_case_056.sh \
	test_case_060.sh \
	test_case_110.sh \
	test_case_113.sh \
	test_case_116.sh \
	test_case_130.sh \
	test_case_135.sh \
	test_case_140.sh \
	test_case_143.sh \
	test_case_145.sh \
	test_case_160.sh \
	test_case_200.sh \
	test_case_210.sh \
	test_case_222.sh \
	test_case_223.sh \
	test_case_226.sh \
	test_case_227.sh \
	test_case_230.sh \
	test_case_235.sh \
	test_case_240.sh \
	test_case_250.sh \
	test_case_253.sh \
	test_case_255.sh \
	test_case_270.sh \
	test_case_295.sh \
	test_case_300.sh \
	test_case_900.sh \
	unique_slug_01.sh \
	unique_slug_02.sh \
	unique_slug_03.sh \
	unique_slug_04.sh \
	unique_slug_05.sh \
	unique_slug_06.sh \
	url_decode_01.sh \
	url_decode_02.sh \
	url_decode_03.sh \
	url_decode_04.sh \
	defect_equals_in_data.sh

check_PROGRAMS = \
	uniqueslug \
	urldecode

CLEANFILES = $(TESTS) \
	out.txt \
	uniqueslug \
	urldecode \
	core \
	tmp.txt

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
	&& echo "SCRIPT_NAME=/api" >> $@ \
	&& echo "export SCRIPT_NAME" >> $@ \
	&& echo "export CONTENT_LENGTH" >> $@ \
	&& echo "export CONTENT_TYPE" >> $@ \
	&& echo "export PATH_INFO" >> $@ \
	&& echo "export REQUEST_METHOD" >> $@ \
	&& echo 'echo $${REQUEST_BODY} | ../src/todoservice >out.txt' >> $@
	
COMMON_POST_ECHO = \
	echo "rm -f out.txt" >> $@ \
	&& chmod +x $@


test_case_010.sh:
	echo "PATH_INFO=/" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"/todos\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"/version\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_013.sh:
	echo "PATH_INFO=/" > $@
	echo "REQUEST_METHOD=HEAD" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_016.sh:
	echo "PATH_INFO=/" > $@
	echo "REQUEST_METHOD=OPTIONS" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Allow: GET, HEAD, OPTIONS\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_020.sh:
	echo "PATH_INFO=/" > $@
	echo "REQUEST_METHOD=PUT" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 405 Method Not Allowed\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Allow: GET, HEAD, OPTIONS\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_050.sh:
	echo "PATH_INFO=/version" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"major\\\">1<\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"minor\\\">0<\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"age\\\">0<\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_053.sh:
	echo "PATH_INFO=/version" > $@
	echo "REQUEST_METHOD=HEAD" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_056.sh:
	echo "PATH_INFO=/version" > $@
	echo "REQUEST_METHOD=OPTIONS" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Allow: GET, HEAD, OPTIONS\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_060.sh:
	echo "PATH_INFO=/version" > $@
	echo "REQUEST_METHOD=PUT" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 405 Method Not Allowed\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Allow: GET, HEAD, OPTIONS\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_110.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo 'echo $${REQUEST_BODY} | ../src/todoservice >/dev/null' >> $@ # Second post, identical content
	echo 'echo $${REQUEST_BODY} | ../src/todoservice >/dev/null' >> $@ # Third post, identical content
	echo "REQUEST_METHOD=GET" >> $@ # Now get /todos
	echo '../src/todoservice >out.txt' >> $@
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/api/todos/my\\\"\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/api/todos/my-test\\\"\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/api/todos/my-test-message\\\"\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_113.sh:
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=HEAD" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_116.sh:
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=OPTIONS" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Allow: GET, HEAD, OPTIONS, POST\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_130.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/api/todos/my\\\"\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_135.sh:
	echo "REQUEST_BODY=data=" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Location: /api/todos/1\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/api/todos/1\\\"\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_140.sh:
	echo "REQUEST_BODY=data=My+t%65st%2" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 400 Bad Request\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_143.sh:
	echo "REQUEST_BODY=data=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 413 Request Entity Too Large\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_145.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/dogs" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 415 Unsupported Media Type\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_160.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=PUT" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 405 Method Not Allowed\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Allow: GET, HEAD, OPTIONS, POST\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_200.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "PATH_INFO=/todos/my" >> $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_210.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "PATH_INFO=/todos/hey" >> $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 404 File Not Found\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_222.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "PATH_INFO=/todos/my" >> $@
	echo "REQUEST_METHOD=HEAD" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_223.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "PATH_INFO=/todos/hey" >> $@
	echo "REQUEST_METHOD=HEAD" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 404 File Not Found\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_226.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "PATH_INFO=/todos/my" >> $@
	echo "REQUEST_METHOD=OPTIONS" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Allow: DELETE, GET, HEAD, OPTIONS, PUT\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_227.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "PATH_INFO=/todos/hey" >> $@
	echo "REQUEST_METHOD=OPTIONS" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 404 File Not Found\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_230.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "REQUEST_BODY=data=My+t%65st%20monster" >> $@
	echo "PATH_INFO=/todos/my" >> $@
	echo "REQUEST_METHOD=PUT" >> $@
	echo 'CONTENT_LENGTH=$${#REQUEST_BODY}' >> $@
	echo 'echo $${REQUEST_BODY} | ../src/todoservice >out.txt' >> $@
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "REQUEST_BODY=" >> $@
	echo "REQUEST_METHOD=GET" >> $@
	echo 'echo $${REQUEST_BODY} | ../src/todoservice >out.txt' >> $@
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"monster\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_235.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "REQUEST_BODY=data=" >> $@
	echo "PATH_INFO=/todos/my" >> $@
	echo "REQUEST_METHOD=PUT" >> $@
	echo 'CONTENT_LENGTH=$${#REQUEST_BODY}' >> $@
	echo 'echo $${REQUEST_BODY} | ../src/todoservice >out.txt' >> $@
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "REQUEST_BODY=" >> $@
	echo "REQUEST_METHOD=GET" >> $@
	echo 'echo $${REQUEST_BODY} | ../src/todoservice >out.txt' >> $@
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_240.sh:
	echo "REQUEST_BODY=data=My+t%65st%2" > $@
	echo "PATH_INFO=/todos/my" >> $@
	echo "REQUEST_METHOD=PUT" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 400 Bad Request\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_250.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos/hey" >> $@
	echo "REQUEST_METHOD=PUT" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 404 File Not Found\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_253.sh:
	echo "REQUEST_BODY=data=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" > $@
	echo "PATH_INFO=/todos/my" >> $@
	echo "REQUEST_METHOD=PUT" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 413 Request Entity Too Large\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_255.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos/my" >> $@
	echo "REQUEST_METHOD=PUT" >> $@
	echo "CONTENT_TYPE=application/dogs" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 415 Unsupported Media Type\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_270.sh:
	echo "REQUEST_BODY=data=My+t%65st%20message" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Location: /api/todos/my\" out.txt >/dev/null || exit 1" >> $@
	echo "PATH_INFO=/todos/my" >> $@
	echo "REQUEST_METHOD=DELETE" >> $@
	echo '../src/todoservice >out.txt' >> $@
	echo "grep \"Status: 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "REQUEST_BODY=" >> $@
	echo "REQUEST_METHOD=GET" >> $@
	echo '../src/todoservice >out.txt' >> $@
	echo "grep \"Status: 404 File Not Found\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_295.sh:
	echo "PATH_INFO=/todos/cat" > $@
	echo "REQUEST_METHOD=POST" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 405 Method Not Allowed\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Allow: DELETE, GET, HEAD, OPTIONS, PUT\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_300.sh:
	echo "PATH_INFO=/todos/my/too/far" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"Status: 404 File Not Found\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	
test_case_900.sh:
	echo "PATH_INFO=/dogs" > $@
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

unique_slug_06.sh: uniqueslug
	echo "./uniqueslug \"\" 1 || exit 1" > $@
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

defect_equals_in_data.sh:
	echo "REQUEST_BODY=data=x=y=4" > $@
	echo "PATH_INFO=/todos" >> $@
	echo "REQUEST_METHOD=POST" >> $@
	echo "CONTENT_TYPE=application/x-www-form-urlencoded" >> $@
	$(DATA_TEST_INIT)
	$(COMMON_ECHO)
	echo "grep \"Location: /api/todos/x\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"Status: 201 Created\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"href=\\\"/api/todos/x\\\"\" out.txt >/dev/null || exit 1" >> $@
	echo "REQUEST_METHOD=GET" >> $@
	echo '../src/todoservice >out.txt' >> $@
	echo "grep \"x=y=4\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)
	




