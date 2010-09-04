TESTS = \
	test_case_050.sh \
	test_case_060.sh \
	test_case_900.sh \
	unique_slug_01.sh \
	unique_slug_02.sh \
	unique_slug_03.sh \
	unique_slug_04.sh \
	unique_slug_05.sh \
	url_decode_01.sh \
	url_decode_02.sh \
	url_decode_03.sh



check_PROGRAMS = \
	uniqueslug \
	urldecode

CLEANFILES = $(TESTS) \
	out.txt \
	uniqueslug \
	urldecode

uniqueslug_LDADD = ../src/libcore.a
uniqueslug_CPPFLAGS = -I$(top_srcdir)/src
urldecode_LDADD = ../src/libcore.a
urldecode_CPPFLAGS = -I$(top_srcdir)/src

COMMON_ECHO = \
	echo "export REQUEST_URI" >> $@ \
	&& echo "export REQUEST_METHOD" >> $@ \
	&& echo "../src/todoservice >out.txt" >> $@
	
COMMON_POST_ECHO = \
	echo "rm -f out.txt" >> $@ \
	&& chmod +x $@


test_case_050.sh:
	echo "REQUEST_URI=/version" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"HTTP/1.1 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"major=\\\"1\\\"\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"minor=\\\"0\\\"\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"age=\\\"0\\\"\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_060.sh:
	echo "REQUEST_URI=/version" > $@
	echo "REQUEST_METHOD=PUT" >> $@
	$(COMMON_ECHO)
	echo "grep \"HTTP/1.1 405 Method not allowed\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_900.sh:
	echo "REQUEST_URI=/dogs" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"HTTP/1.1 404 File not found\" out.txt >/dev/null || exit 1" >> $@
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
	echo "./urldecode \"h%65%6C%6\" hello || exit 0" > $@ # invalid input, expect failure
	$(COMMON_POST_ECHO)




