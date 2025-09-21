import { Box, rem, type BoxProps } from '@mantine/core';
import { GlassSx, mantineSpace } from '@/define';
import Graph from '@/ui/Graph/Canvas';

export default function Page({ style, ...props }: BoxProps) {
  return (
    <Box
      style={{
        flexGrow: 1,
        width: '100%',
        backgroundColor: 'var(--mantine-color-secondaryDark-9)',
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
