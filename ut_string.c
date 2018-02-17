#include "utstring.h"

UT_string *buf = NULL;

int main(void)
{
    UT_string *tmp = NULL;
    long i = 0;

    utstring_new(tmp);
    utstring_new(buf);
    printf("[init str]: len=%ld\n", utstring_len(buf));

    utstring_bincpy(buf,"hello",strlen("hello"));
    utstring_bincpy(tmp,"str2:hello",strlen("str2:hello"));
    printf("[str <%ld>]: buf=%s\n", utstring_len(buf), utstring_body(buf));
    printf("[str <%ld>]: tmp=%s\n", utstring_len(tmp), utstring_body(tmp));

    utstring_clear(buf);

    utstring_printf(buf, "%s %d", __FILE__, __LINE__);
    printf("[str <%ld>]: buf=%s\n", utstring_len(buf), utstring_body(buf));

    utstring_concat(buf, tmp);
    printf("[str <%ld>]: buf=%s\n", utstring_len(buf), utstring_body(buf));

    i = utstring_find(buf, 0, "hello", strlen("hello"));
    printf("[find str \"%s\"]: pos = %ld\n", "hello", i);
    
    utstring_free(buf);
    utstring_free(tmp);
    return 0;
}
