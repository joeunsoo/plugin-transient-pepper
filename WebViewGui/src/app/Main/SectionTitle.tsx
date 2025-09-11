import { testOpacity } from '@/define';
import { uesControlStore } from '@/store/ControlStore';
import type { UIProps } from '@/types/UI';
import Box, { type BoxProps } from '@mui/material/Box';

export default function Component({
  children,
  sx,
  ignoreBypass=false,
  addTest=[],
  ...props
}: UIProps & BoxProps) {
  const { bypassed } = uesControlStore();

  return (
    <Box
      sx={{
        fontWeight: 'var(--mui-fontWeight-lg)',
        fontSize: 'var(--mui-fontSize-sm)',
        color: 'var(--mui-palette-common-white)',
        opacity: testOpacity([
          bypassed && !ignoreBypass,
          ...addTest
        ]),
        ...sx,
      }}
      {...props}
    >
      {children}
    </Box>
  );
}
