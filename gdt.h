struct gdt_entry
{
	uint16 limitlow;
	uint16 baselow;
	uint8  basemiddle;
	uint8  accessbyte;
	uint8  limithighandflag;//4 bits for limithigh 4 higher bits  for flags
	uint8  basehigh;
}_attribute_((packed));

typedef struct gdt_entry gdt_entry_s;
//hi sir How r u ?
struct gdt_desc
{
	uint16 size;
	uint32 gdt_address;
	
}

typedef struct gdt_desc gdt_desc_s;
