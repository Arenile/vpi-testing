#include <vpi_user.h>

static int hello_compiletf(char* user_data) {
    return 0;
}

static int hello_calltf(char* user_data) {

    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
    vpiHandle argv = vpi_iterate(vpiArgument, callh);
    vpiHandle item;

    item = vpi_scan(argv);
    struct t_vpi_value argval;
    int value;

    argval.format = vpiIntVal;
    vpi_get_value(item, &argval);
    value = argval.value.integer;

    vpi_printf("HELLO VERILOG!\n");
    vpi_printf("RECEIVED = %i\n", value);
    return 0;
}

void hello_register() {
    s_vpi_systf_data tf_data;

    tf_data.type = vpiSysTask;
    tf_data.tfname = "$hello";
    tf_data.calltf = hello_calltf;
    tf_data.compiletf = hello_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = "$hello";
    vpiHandle res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}

void (*vlog_startup_routines[])() = {
    hello_register,
    0
};