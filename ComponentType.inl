
flocal len_string print_enum_name_PointDisplayType(u32 field)
{
	len_string s = l_string(256);
	if ( POINT_DISPLAY_TYPE_NONE & field )
	{
		append_to_len_string(&s, "POINT_DISPLAY_TYPE_NONE\n");
	}
	if ( POINT_DISPLAY_TYPE_QUAD & field )
	{
		append_to_len_string(&s, "POINT_DISPLAY_TYPE_QUAD\n");
	}
	if ( POINT_DISPLAY_TYPE_CIRCLE & field )
	{
		append_to_len_string(&s, "POINT_DISPLAY_TYPE_CIRCLE\n");
	}
	return s;
}
flocal len_string print_enum_name_PointDisplayType_using_equals(u32 field)
{
	len_string s = l_string(256);
	if ( POINT_DISPLAY_TYPE_NONE == field )
	{
		append_to_len_string(&s, "POINT_DISPLAY_TYPE_NONE");
	}
	if ( POINT_DISPLAY_TYPE_QUAD == field )
	{
		append_to_len_string(&s, "POINT_DISPLAY_TYPE_QUAD");
	}
	if ( POINT_DISPLAY_TYPE_CIRCLE == field )
	{
		append_to_len_string(&s, "POINT_DISPLAY_TYPE_CIRCLE");
	}
	return s;
}

flocal u32 PointDisplayType_name_to_bits(char* name)
{
	if ( streq("POINT_DISPLAY_TYPE_NONE", name, strlen(name)) )
	{
		return (u32)POINT_DISPLAY_TYPE_NONE;
	}
	if ( streq("POINT_DISPLAY_TYPE_QUAD", name, strlen(name)) )
	{
		return (u32)POINT_DISPLAY_TYPE_QUAD;
	}
	if ( streq("POINT_DISPLAY_TYPE_CIRCLE", name, strlen(name)) )
	{
		return (u32)POINT_DISPLAY_TYPE_CIRCLE;
	}
}

global_variable char* PointDisplayType_name_arr[] = 
{
	"POINT_DISPLAY_TYPE_NONE",
	"POINT_DISPLAY_TYPE_QUAD",
	"POINT_DISPLAY_TYPE_CIRCLE"
};

global_variable u32 PointDisplayType_val_arr[] = 
{
	0,
	1,
	2
};

global_variable u32 PointDisplayType_field_count = 3;

flocal len_string print_enum_name_LineDisplayType(u32 field)
{
	len_string s = l_string(256);
	if ( LINE_DISPLAY_TYPE_NONE & field )
	{
		append_to_len_string(&s, "LINE_DISPLAY_TYPE_NONE\n");
	}
	if ( LINE_DISPLAY_TYPE_STROKE & field )
	{
		append_to_len_string(&s, "LINE_DISPLAY_TYPE_STROKE\n");
	}
	return s;
}
flocal len_string print_enum_name_LineDisplayType_using_equals(u32 field)
{
	len_string s = l_string(256);
	if ( LINE_DISPLAY_TYPE_NONE == field )
	{
		append_to_len_string(&s, "LINE_DISPLAY_TYPE_NONE");
	}
	if ( LINE_DISPLAY_TYPE_STROKE == field )
	{
		append_to_len_string(&s, "LINE_DISPLAY_TYPE_STROKE");
	}
	return s;
}

flocal u32 LineDisplayType_name_to_bits(char* name)
{
	if ( streq("LINE_DISPLAY_TYPE_NONE", name, strlen(name)) )
	{
		return (u32)LINE_DISPLAY_TYPE_NONE;
	}
	if ( streq("LINE_DISPLAY_TYPE_STROKE", name, strlen(name)) )
	{
		return (u32)LINE_DISPLAY_TYPE_STROKE;
	}
}

global_variable char* LineDisplayType_name_arr[] = 
{
	"LINE_DISPLAY_TYPE_NONE",
	"LINE_DISPLAY_TYPE_STROKE"
};

global_variable u32 LineDisplayType_val_arr[] = 
{
	0,
	1
};

global_variable u32 LineDisplayType_field_count = 2;

flocal len_string print_enum_name_MeshDisplayType(u32 field)
{
	len_string s = l_string(256);
	if ( MESH_DISPLAY_TYPE_NONE & field )
	{
		append_to_len_string(&s, "MESH_DISPLAY_TYPE_NONE\n");
	}
	if ( MESH_DISPLAY_TYPE_WIRES & field )
	{
		append_to_len_string(&s, "MESH_DISPLAY_TYPE_WIRES\n");
	}
	if ( MESH_DISPLAY_TYPE_FILL & field )
	{
		append_to_len_string(&s, "MESH_DISPLAY_TYPE_FILL\n");
	}
	return s;
}
flocal len_string print_enum_name_MeshDisplayType_using_equals(u32 field)
{
	len_string s = l_string(256);
	if ( MESH_DISPLAY_TYPE_NONE == field )
	{
		append_to_len_string(&s, "MESH_DISPLAY_TYPE_NONE");
	}
	if ( MESH_DISPLAY_TYPE_WIRES == field )
	{
		append_to_len_string(&s, "MESH_DISPLAY_TYPE_WIRES");
	}
	if ( MESH_DISPLAY_TYPE_FILL == field )
	{
		append_to_len_string(&s, "MESH_DISPLAY_TYPE_FILL");
	}
	return s;
}

flocal u32 MeshDisplayType_name_to_bits(char* name)
{
	if ( streq("MESH_DISPLAY_TYPE_NONE", name, strlen(name)) )
	{
		return (u32)MESH_DISPLAY_TYPE_NONE;
	}
	if ( streq("MESH_DISPLAY_TYPE_WIRES", name, strlen(name)) )
	{
		return (u32)MESH_DISPLAY_TYPE_WIRES;
	}
	if ( streq("MESH_DISPLAY_TYPE_FILL", name, strlen(name)) )
	{
		return (u32)MESH_DISPLAY_TYPE_FILL;
	}
}

global_variable char* MeshDisplayType_name_arr[] = 
{
	"MESH_DISPLAY_TYPE_NONE",
	"MESH_DISPLAY_TYPE_WIRES",
	"MESH_DISPLAY_TYPE_FILL"
};

global_variable u32 MeshDisplayType_val_arr[] = 
{
	0,
	1,
	2
};

global_variable u32 MeshDisplayType_field_count = 3;

flocal len_string print_enum_name_QuadType(u32 field)
{
	len_string s = l_string(256);
	if ( QUAD_TYPE_SCREEN_SPACE & field )
	{
		append_to_len_string(&s, "QUAD_TYPE_SCREEN_SPACE\n");
	}
	if ( QUAD_TYPE_WORLD_SPACE & field )
	{
		append_to_len_string(&s, "QUAD_TYPE_WORLD_SPACE\n");
	}
	return s;
}
flocal len_string print_enum_name_QuadType_using_equals(u32 field)
{
	len_string s = l_string(256);
	if ( QUAD_TYPE_SCREEN_SPACE == field )
	{
		append_to_len_string(&s, "QUAD_TYPE_SCREEN_SPACE");
	}
	if ( QUAD_TYPE_WORLD_SPACE == field )
	{
		append_to_len_string(&s, "QUAD_TYPE_WORLD_SPACE");
	}
	return s;
}

flocal u32 QuadType_name_to_bits(char* name)
{
	if ( streq("QUAD_TYPE_SCREEN_SPACE", name, strlen(name)) )
	{
		return (u32)QUAD_TYPE_SCREEN_SPACE;
	}
	if ( streq("QUAD_TYPE_WORLD_SPACE", name, strlen(name)) )
	{
		return (u32)QUAD_TYPE_WORLD_SPACE;
	}
}

global_variable char* QuadType_name_arr[] = 
{
	"QUAD_TYPE_SCREEN_SPACE",
	"QUAD_TYPE_WORLD_SPACE"
};

global_variable u32 QuadType_val_arr[] = 
{
	0,
	1
};

global_variable u32 QuadType_field_count = 2;

flocal len_string print_enum_name_ComponentType(u32 field)
{
	len_string s = l_string(256);
	if ( COMPONENT_TYPE_NONE & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_NONE\n");
	}
	if ( COMPONENT_TYPE_PT & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_PT\n");
	}
	if ( COMPONENT_TYPE_SIZE & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_SIZE\n");
	}
	if ( COMPONENT_TYPE_LINE & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_LINE\n");
	}
	if ( COMPONENT_TYPE_HAS_CHILDREN & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_HAS_CHILDREN\n");
	}
	if ( COMPONENT_TYPE_COLOR & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_COLOR\n");
	}
	if ( COMPONENT_TYPE_MASS & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_MASS\n");
	}
	if ( COMPONENT_TYPE_VELOCITY & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_VELOCITY\n");
	}
	if ( COMPONENT_TYPE_ACCELERATION & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_ACCELERATION\n");
	}
	if ( COMPONENT_TYPE_BOID & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_BOID\n");
	}
	if ( COMPONENT_TYPE_FLAGGED_DELETION & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_FLAGGED_DELETION\n");
	}
	if ( COMPONENT_TYPE_FROZEN & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_FROZEN\n");
	}
	if ( COMPONENT_TYPE_QUAD & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_QUAD\n");
	}
	if ( COMPONENT_TYPE_GLYPH & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_GLYPH\n");
	}
	if ( COMPONENT_TYPE_STATIC_MESH & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_STATIC_MESH\n");
	}
	if ( COMPONENT_TYPE_CLICKABLE & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_CLICKABLE\n");
	}
	if ( COMPONENT_TYPE_MESH_MEMBER & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_MESH_MEMBER\n");
	}
	if ( COMPONENT_TYPE_POSITION & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_POSITION\n");
	}
	if ( COMPONENT_TYPE_TEXTURE & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_TEXTURE\n");
	}
	if ( COMPONENT_TYPE_AGENT_TYPE & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_AGENT_TYPE\n");
	}
	if ( COMPONENT_TYPE_TIMERS & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_TIMERS\n");
	}
	if ( COMPONENT_TYPE_HAS_PERSISTENT_TARGET & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_HAS_PERSISTENT_TARGET\n");
	}
	if ( COMPONENT_TYPE_PLAYER_CONTROLLABLE & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_PLAYER_CONTROLLABLE\n");
	}
	if ( COMPONENT_TYPE_CLICKABLE_REFLECTION & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_CLICKABLE_REFLECTION\n");
	}
	if ( COMPONENT_TYPE_SAVED_W_LEVEL & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_SAVED_W_LEVEL\n");
	}
	if ( COMPONENT_TYPE_NOT_NULL & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_NOT_NULL\n");
	}
	if ( COMPONENT_TYPE_PLAYER_TONGUE & field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_PLAYER_TONGUE\n");
	}
	return s;
}
flocal len_string print_enum_name_ComponentType_using_equals(u32 field)
{
	len_string s = l_string(256);
	if ( COMPONENT_TYPE_NONE == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_NONE");
	}
	if ( COMPONENT_TYPE_PT == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_PT");
	}
	if ( COMPONENT_TYPE_SIZE == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_SIZE");
	}
	if ( COMPONENT_TYPE_LINE == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_LINE");
	}
	if ( COMPONENT_TYPE_HAS_CHILDREN == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_HAS_CHILDREN");
	}
	if ( COMPONENT_TYPE_COLOR == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_COLOR");
	}
	if ( COMPONENT_TYPE_MASS == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_MASS");
	}
	if ( COMPONENT_TYPE_VELOCITY == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_VELOCITY");
	}
	if ( COMPONENT_TYPE_ACCELERATION == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_ACCELERATION");
	}
	if ( COMPONENT_TYPE_BOID == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_BOID");
	}
	if ( COMPONENT_TYPE_FLAGGED_DELETION == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_FLAGGED_DELETION");
	}
	if ( COMPONENT_TYPE_FROZEN == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_FROZEN");
	}
	if ( COMPONENT_TYPE_QUAD == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_QUAD");
	}
	if ( COMPONENT_TYPE_GLYPH == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_GLYPH");
	}
	if ( COMPONENT_TYPE_STATIC_MESH == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_STATIC_MESH");
	}
	if ( COMPONENT_TYPE_CLICKABLE == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_CLICKABLE");
	}
	if ( COMPONENT_TYPE_MESH_MEMBER == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_MESH_MEMBER");
	}
	if ( COMPONENT_TYPE_POSITION == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_POSITION");
	}
	if ( COMPONENT_TYPE_TEXTURE == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_TEXTURE");
	}
	if ( COMPONENT_TYPE_AGENT_TYPE == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_AGENT_TYPE");
	}
	if ( COMPONENT_TYPE_TIMERS == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_TIMERS");
	}
	if ( COMPONENT_TYPE_HAS_PERSISTENT_TARGET == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_HAS_PERSISTENT_TARGET");
	}
	if ( COMPONENT_TYPE_PLAYER_CONTROLLABLE == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_PLAYER_CONTROLLABLE");
	}
	if ( COMPONENT_TYPE_CLICKABLE_REFLECTION == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_CLICKABLE_REFLECTION");
	}
	if ( COMPONENT_TYPE_SAVED_W_LEVEL == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_SAVED_W_LEVEL");
	}
	if ( COMPONENT_TYPE_NOT_NULL == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_NOT_NULL");
	}
	if ( COMPONENT_TYPE_PLAYER_TONGUE == field )
	{
		append_to_len_string(&s, "COMPONENT_TYPE_PLAYER_TONGUE");
	}
	return s;
}

flocal u32 ComponentType_name_to_bits(char* name)
{
	if ( streq("COMPONENT_TYPE_NONE", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_NONE;
	}
	if ( streq("COMPONENT_TYPE_PT", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_PT;
	}
	if ( streq("COMPONENT_TYPE_SIZE", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_SIZE;
	}
	if ( streq("COMPONENT_TYPE_LINE", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_LINE;
	}
	if ( streq("COMPONENT_TYPE_HAS_CHILDREN", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_HAS_CHILDREN;
	}
	if ( streq("COMPONENT_TYPE_COLOR", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_COLOR;
	}
	if ( streq("COMPONENT_TYPE_MASS", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_MASS;
	}
	if ( streq("COMPONENT_TYPE_VELOCITY", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_VELOCITY;
	}
	if ( streq("COMPONENT_TYPE_ACCELERATION", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_ACCELERATION;
	}
	if ( streq("COMPONENT_TYPE_BOID", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_BOID;
	}
	if ( streq("COMPONENT_TYPE_FLAGGED_DELETION", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_FLAGGED_DELETION;
	}
	if ( streq("COMPONENT_TYPE_FROZEN", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_FROZEN;
	}
	if ( streq("COMPONENT_TYPE_QUAD", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_QUAD;
	}
	if ( streq("COMPONENT_TYPE_GLYPH", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_GLYPH;
	}
	if ( streq("COMPONENT_TYPE_STATIC_MESH", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_STATIC_MESH;
	}
	if ( streq("COMPONENT_TYPE_CLICKABLE", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_CLICKABLE;
	}
	if ( streq("COMPONENT_TYPE_MESH_MEMBER", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_MESH_MEMBER;
	}
	if ( streq("COMPONENT_TYPE_POSITION", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_POSITION;
	}
	if ( streq("COMPONENT_TYPE_TEXTURE", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_TEXTURE;
	}
	if ( streq("COMPONENT_TYPE_AGENT_TYPE", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_AGENT_TYPE;
	}
	if ( streq("COMPONENT_TYPE_TIMERS", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_TIMERS;
	}
	if ( streq("COMPONENT_TYPE_HAS_PERSISTENT_TARGET", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_HAS_PERSISTENT_TARGET;
	}
	if ( streq("COMPONENT_TYPE_PLAYER_CONTROLLABLE", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_PLAYER_CONTROLLABLE;
	}
	if ( streq("COMPONENT_TYPE_CLICKABLE_REFLECTION", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_CLICKABLE_REFLECTION;
	}
	if ( streq("COMPONENT_TYPE_SAVED_W_LEVEL", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_SAVED_W_LEVEL;
	}
	if ( streq("COMPONENT_TYPE_NOT_NULL", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_NOT_NULL;
	}
	if ( streq("COMPONENT_TYPE_PLAYER_TONGUE", name, strlen(name)) )
	{
		return (u32)COMPONENT_TYPE_PLAYER_TONGUE;
	}
}

global_variable char* ComponentType_name_arr[] = 
{
	"COMPONENT_TYPE_NONE",
	"COMPONENT_TYPE_PT",
	"COMPONENT_TYPE_SIZE",
	"COMPONENT_TYPE_LINE",
	"COMPONENT_TYPE_HAS_CHILDREN",
	"COMPONENT_TYPE_COLOR",
	"COMPONENT_TYPE_MASS",
	"COMPONENT_TYPE_VELOCITY",
	"COMPONENT_TYPE_ACCELERATION",
	"COMPONENT_TYPE_BOID",
	"COMPONENT_TYPE_FLAGGED_DELETION",
	"COMPONENT_TYPE_FROZEN",
	"COMPONENT_TYPE_QUAD",
	"COMPONENT_TYPE_GLYPH",
	"COMPONENT_TYPE_STATIC_MESH",
	"COMPONENT_TYPE_CLICKABLE",
	"COMPONENT_TYPE_MESH_MEMBER",
	"COMPONENT_TYPE_POSITION",
	"COMPONENT_TYPE_TEXTURE",
	"COMPONENT_TYPE_AGENT_TYPE",
	"COMPONENT_TYPE_TIMERS",
	"COMPONENT_TYPE_HAS_PERSISTENT_TARGET",
	"COMPONENT_TYPE_PLAYER_CONTROLLABLE",
	"COMPONENT_TYPE_CLICKABLE_REFLECTION",
	"COMPONENT_TYPE_SAVED_W_LEVEL",
	"COMPONENT_TYPE_NOT_NULL",
	"COMPONENT_TYPE_PLAYER_TONGUE"
};

global_variable u32 ComponentType_val_arr[] = 
{
	0,
	1,
	2,
	4,
	8,
	16,
	32,
	64,
	128,
	256,
	512,
	1024,
	2048,
	4096,
	8192,
	16384,
	32768,
	65536,
	131072,
	262144,
	524288,
	1048576,
	2097152,
	4194304,
	8388608,
	16777216,
	33554432
};

global_variable u32 ComponentType_field_count = 27;
