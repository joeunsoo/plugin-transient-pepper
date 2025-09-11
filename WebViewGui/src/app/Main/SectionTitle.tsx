import Box, { type BoxProps } from '@mui/material/Box';

export default function Component({
  children, sx, ...props
}: BoxProps) {
  return (
    <Box
      sx={{
        fontWeight: 'var(--mui-fontWeight-lg)',
        fontSize: 'var(--mui-fontSize-sm)',
        color: 'var(--mui-palette-common-white)',
        ...sx,
      }}
      {...props}
    >
      {children}
    </Box>
  );
}
