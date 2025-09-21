import { GlassSx, mantineSpace, } from '@/define';
import Graph from '@/ui/Graph/Canvas';
import { Box, rem, type BoxProps } from '@mantine/core';

export default function Page({
  style, ...props
}: BoxProps) {
  return (
    <Box
      style={{
        flexGrow: 1,
        width: '100%',
        backgroundColor: 'var(--mui-palette-secondary-blackest)',
        borderRadius: rem(mantineSpace * 3),
        ...style,
      }}
      sx={{
        ...GlassSx,
        '& > svg, canvas': {
          borderRadius: rem(mantineSpace * 3),
        },
      }}
      {...props}
    >
      <Graph />
    </Box>
  );
}
