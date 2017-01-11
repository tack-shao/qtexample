//struct offset test
#include <stdio.h>



typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;


struct rb_node {
    unsigned long  __rb_parent_color;
    struct rb_node *rb_right;
    struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));
    /* The alignment might seem pointless, but allegedly CRIS needs it */


struct ceph_pg_pool_info {
    struct rb_node node;
    s64 id;
    u8 type;
    u8 size;
    u8 crush_ruleset;
    u8 object_hash;
    u32 pg_num, pgp_num;
    int pg_num_mask, pgp_num_mask;
    s64 read_tier;
    s64 write_tier; /* wins for read+write ops */
    u64 flags;
    char *name;
};

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)


/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({                      \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

#define	rb_entry(ptr, type, member) container_of(ptr, type, member)



int main(void)
{
    struct rb_node *parent = NULL;
    struct ceph_pg_pool_info *pi = NULL;
    pi = rb_entry(parent, struct ceph_pg_pool_info, node);

    printf("offset :%d\n", offsetof(struct ceph_pg_pool_info, node));
    typeof(int *) a,b;

    printf("Hello World!\n");
    return 0;
}

/*result:
offset :0
Hello World!

*/

