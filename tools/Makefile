hostprogs-y	:= checksum
always		:= $(hostprogs-y)

$(addprefix $(obj)/,$(filter-out checksum,$(always))): $(obj)/checksum
