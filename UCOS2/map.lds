SECTIONS
{
	. = 0x23E00000;
	
	.text : {
		S5PV210/source/start.o
		* (.text)
	}
    		
	.data : {
		* (.data)
	}
	
	bss_start = .; 
	.bss : {
		* (.bss)
	}
	
	bss_end  = .;	
}

