#ifndef MCSTRING_UNCONST
#define MCSTRING_UNCONST

#define UNCONST_MEMBER(type, struct_ptr, struct_type, struct_member) (*(type *)((unsigned char*)(struct_ptr) + offsetof(struct_type, struct_member)))

#endif /* MCSTRING_UNCONST */
