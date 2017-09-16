#include "jlibs.h"
#include "dblog.h"
#include "cserv.h"

extern skb2u_t skb2u;

//char *prepare_jmsd01(msd01_t msd01)
uint32_t prepare_jmsd01(msd01_t msd01)
{
    char* ret_strings = NULL;
    //char ret_strings[512];
	uint32_t len = 0;

	debug_log("jms: prep jm1fx ...\n");

    json_t *root = json_object();
    json_t *json_arr = json_array();

    json_object_set_new(root, "module", json_integer(1));
    json_object_set_new(root, "screen", json_integer(2));
    json_object_set_new(root, "func", json_integer(3));
    json_object_set_new(root, "dint", json_boolean(1));
    json_object_set_new(root, "ddbl", json_real(2.14));
    json_object_set_new(root, "dstr", json_string("Mod:Scrn:Func"));

    json_object_set_new(root, "data", json_arr);

	json_array_append(json_arr, json_integer(11));
	json_array_append(json_arr, json_integer(12));
	json_array_append(json_arr, json_integer(12));
	json_array_append(json_arr, json_integer(9));

#if 1
	ret_strings = json_dumps(root, 0);
	len = strlen(ret_strings);//sizeof(ret_strings);
	if (len > 0)
	{
		memset(skb2u.send_buf, 0, SEND_LEN);
		memcpy(&skb2u.send_buf, ret_strings, len);
		skb2u.send_len = len;
		//puts(ret_strings);

    	debug_log("jms: size %lu, \n %s\n",
			strlen(ret_strings), ret_strings);
	}
#endif
	return len;

}


	

char *gen_jdata_hompg()
{

    char* ret_strings = NULL;

    json_t *root = json_object();
    json_t *json_arr = json_array();

    json_object_set_new(root, "destID", json_integer(1));
    json_object_set_new(root, "command", json_string("enable"));
    json_object_set_new(root, "respond", json_integer(0));
    json_object_set_new(root, "data", json_arr);

	json_array_append(json_arr, json_integer(11));
	json_array_append(json_arr, json_integer(12));
	json_array_append(json_arr, json_integer(12));
	json_array_append(json_arr, json_integer(9));

	ret_strings =json_dumps(root, 0);
	puts(ret_strings);

}
