@ set device_types = unique(graph_instance['devices'] | map(attribute='type'))
@ set device_type_arrays = pymap(get_device_array, device_types)
@ set add_edges_args = mformat("device_t* %s", device_type_arrays) | join(', ')

void add_edges({{ add_edges_args }}) {

	@ set device_types = unique(graph_instance['devices'] | map(attribute='type'))

	// Connections:

	device_t* src_dev;
	device_t* dst_dev;

	int src_pin;
	int dst_pin;

	dst_list_t dsts;

	// ---

	@ for edge in graph_instance['edges']

	    // {{ edge }}

	    @ set src_device = edge['src'][0]
	    @ set dst_device = edge['dst'][0]

	    @ set src_pin_name = edge['src'][1]
	    @ set dst_pin_name = edge['dst'][1]

	    @ set src_device_index = schema.get_device_index(src_device)
	    @ set dst_device_index = schema.get_device_index(dst_device)

	    @ set src_device_type = schema.get_device(src_device)['type']
	    @ set dst_device_type = schema.get_device(dst_device)['type']

	    @ set src_pin = schema.get_pin_index(src_device_type, src_pin_name, 'output')
	    @ set dst_pin = schema.get_pin_index(dst_device_type, dst_pin_name, 'input')

	    src_dev = {{ get_device_array(src_device_type) }} + {{ src_device_index }};
	    dst_dev = {{ get_device_array(dst_device_type) }} + {{ dst_device_index }};

	    src_pin = {{ src_pin }};
	    dst_pin = {{ dst_pin }};

	    dsts = (*src_dev).getPortDestinations(src_pin);

	    dsts.push_back(destination_t(dst_dev, dst_pin));

	    // printf("destinations = %d\n", dsts.size());

	@ endfor

}
