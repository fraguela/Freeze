## Freeze library </p>

 Freeze is a C++ library to capture runtime variables and turn them into compile-time constants. Its purpose is to help compilers generate code that is as efficient as possible by turning variables that are assigned only once during the execution of a program, typically during the initializacion/configuration stage, into constants. 
 
 For this, users must declare the variables that are assigned only once during the execution and can thus become constants using the macro `FREEZE(type, variable)`. Also, the extern declarations of these variables must have the form `EXTERN_FREEZE(type, variable)`.
 
 Once the user has performed this labeling, Freeze follows a 2 stage approach to achieve this. Namely, two binaries must be built and executed in sequence:
 
1. A capture binary must be built by defining the macro `-DFREEZE_CAPTURE_MODE` during its compilation and linking with `libfreeze.a`. The purpose of this binary is to capture the assignments to the labeled variables and store their values in a hidden file called `.freezes.h`. 

2. Once the capture binary has been run, the binary that benefits from the values captured defining them as constants, which we call the frozen binary, can be built. This is achieved by defining the macro `-DFROZEN_MODE` during its compilation.

If neither of the macros above is defined during the compilation, Freeze neither collects values nor replaces the variables as constants, the labeled variables acting thus as in a regular application without Freeze.

### Caveats

- The capture binary generates `.freezes.h` in the directory where it is executed. Therefore the compilation of the frozen binary must include that directory in the header path in order to find the captured data.

- Relatedly, since `.freezes.h` has always the same name, multiple frozen binaries in the same directory must be built in sequence (no `make -j`), as the parallel execution of different capture binaries in the same directory would overwrite the same file.
 
- The capture binary must be able to dump to a file the captured values. This is achieved using the `operator <<` overload for `std::ostream`.  This operator is already defined for built-in types, but user-defined types require
writing a free function of the form:


		std::ostream& operator << ( std::ostream& os, T const& value ) {
			os << convertMyTypeToString( value );
			return os;
		}


	where ```T``` is your type and ```convertMyTypeToString``` is where you'll write whatever code is necessary to make your type printable - it doesn't have to be in another function. You can see an example in the test `tests/test_struct.cpp`.

	You should put this function in the same namespace as your type and it has to be declared before including Freeze's header.

- The user-defined types of frozen variables must also be fully declared before including Freeze's header. The reason is that the frozen binary must be able to build these frozen variables as constants, which requires this information.

- If you compile in debug mode (no `NDEBUG`), Freeze will check:
   - In the capture binary, that captured variables are only assigned once.   
	- In the frozen binary, that values that would be assigned to the frozen constants match their frozen value. Notice that for user-defined data types this requires defining an `operator ==` for our type `T` of the form
	
			bool operator==(const T& other) const {
				...
			}
	An example on this can be found in the test `tests/test_struct.cpp`.
	
### License

Freeze is available under the MIT license.
