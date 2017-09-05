int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	return 0;
}

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	return 0;
}

/*

 * gadget_driver 需要的函数

 */
int usb_gadget_handle_interrupts(int index)
{
	return 0;
}