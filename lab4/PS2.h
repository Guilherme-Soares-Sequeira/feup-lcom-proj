#define MOUSE_IRQ 12
#define MOUSE_HOOK_ID 16

/* First packet byte structure*/

#define MOUSE_LB BIT(0)
#define MOUSE_RB BIT(1)
#define MOUSE_MB BIT(2)
#define MOUSE_FBYTE BIT(3)
#define MOUSE_XSIGN BIT(4)
#define MOUSE_YSIGN BIT(5)
#define MOUSE_XOVFL BIT(6)
#define MOUSE_YOVFL BIT(7)


/* Check if number is positive or negative */

#define NEG BIT(7)


/* Shift amounts */

#define MOUSE_XSIGN_SHIFT 4
