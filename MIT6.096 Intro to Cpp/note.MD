1. Default arguments: only write in header file; do not write the default arguments in implementation if you have separate header and cpp.
2. static member : if you have separate header and cpp, do not need the static keyword in cpp.
   Golden Rule: The static keyword is only used with the declaration of a static member, inside the class definition, but not with the definition of that static member.
3. when writing template class/function, cannot have separate header and cpp file.