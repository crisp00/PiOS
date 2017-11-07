extern void _krnl_main(){
    __asm__("cli\n\t"
            "hlt");
}