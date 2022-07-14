#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
        int day;
        int month;
        int year;
        struct list_head list;
};

static LIST_HEAD(birthday_list);

int simple_init(void)
{
	int i;
	struct birthday *ptr;

	printk("Loading module\n");
	for (i = 0; i < 5; i++){

		struct birthday *person;
		person = kmalloc(sizeof(person), GFP_KERNEL);
		person->day = 2 + i;
		person->month = 3 + i;
		person->year = 1995 + 2 * i;
		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);

		list_for_each_entry(ptr, &birthday_list, list)
		        printk("+> %d/%d/%d\n", ptr->year, ptr->month, ptr->day);
		printk("----");
	}

        return 0;
}

void simple_exit(void){

	struct birthday *ptr, *tmp;
        printk(KERN_INFO "Removing Module\n");

	list_for_each_entry_safe(ptr, tmp, &birthday_list, list){

		list_del(&ptr->list);
                kfree(ptr);

		list_for_each_entry(ptr, &birthday_list, list){
		        printk("-> %d/%d/%d\n", ptr->year, ptr->month, ptr->day);
		}
		printk("----");

	}


}

module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple module");
MODULE_AUTHOR("SGG");

