import { GlassSx,  } from '@/define';
import Box, { type BoxProps } from '@mui/material/Box';

export default function Page({
  sx, ...props
}: BoxProps) {
  return (
    <Box
      sx={{
        flexGrow: 1,
        width:'100%',
        backgroundColor: 'var(--mui-palette-secondary-blackest)',
        borderRadius: 3,
        ...GlassSx,
        ...sx,
      }}
      {...props}
    >

    </Box>
  );
}
