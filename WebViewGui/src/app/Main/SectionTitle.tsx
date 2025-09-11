import Box, { type BoxProps } from '@mui/material/Box';

export default function Component({
  children, sx, ...props
}: BoxProps) {
  return (
    <Box
      sx={{
        px: 5,
        fontWeight: 'var(--mui-fontWeight-lg)',
        fontSize: 'var(--mui-fontSize-sm)',
        color: 'var(--mui-palette-info-lightermost)',
        pt:3,
        pb:2.5,
        ...sx,
      }}
      {...props}
    >
      {children}
    </Box>
  );
}
