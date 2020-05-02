# lib_wrapper
	This repository includes wrapper for pthread, socket and openssl.

	Intentions
		* Implement thread pool
		* Implement socket functionality for dev's ease

	To Compile the files, use
		gcc file_name.c lib/lib_to_use/.c_file -o file_name -std=c11 -Wall

	[Bug]
		thread lib can give segmentation fault (meaning it is using some unauthorized memory, I think thread locking is required in pool)