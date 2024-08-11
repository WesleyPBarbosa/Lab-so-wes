/*  hello-1.c - The simplest kernel module.
 *
 *  Copyright (C) 2001 by Peter Jay Salzman
 *
 *  08/02/2006 - Updated by Rodrigo Rubira Branco <rodrigo@kernelhacking.com>
 */

/* Kernel Programming */
#define MODULE
#define LINUX


#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */


static int __init comecar_modulo(void)
{
   printk("<1>Ola Mundo 1.\n");
	
   // A non 0 return means init_module failed; module can't be loaded.
   return 0;
}


static void __exitterminar_modulo(void)
{
  printk(KERN_ALERT "Adeus Mundo 1.\n");
}  

comecar_modulo();
terminar_modulo();

MODULE_LICENSE("GPL");