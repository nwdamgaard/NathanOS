
//a simple function called "example_function" that takes no arguments.
//It will simply set a 32-bit integer variable to 10 then return.
func example_function () (
    var int32 myvar;
    set myvar 10;
    return;
);

func main () (
    call example_function ();
);