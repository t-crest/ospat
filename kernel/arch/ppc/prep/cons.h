/*
 * POK header
 * 
 * The following file is a part of the POK project. Any modification should
 * made according to the POK licence. You CANNOT use this file or a part of
 * this file is this part of a file for your own project
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 * Copyright (c) 2007-2009 POK team 
 *
 * Created by julien on Thu Jan 15 23:34:13 2009 
 */


#ifndef __POK_CONS_H__
#define __POK_CONS_H__


#ifdef POK_NEEDS_QEMU_SETUP
 #if defined (POK_NEEDS_CONSOLE) || defined (POK_NEEDS_DEBUG)
int			pok_cons_init(void);
 #endif
#endif

#endif
