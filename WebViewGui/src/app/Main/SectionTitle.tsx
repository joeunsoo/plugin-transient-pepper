import { testOpacity } from '@/define';
import { uesControlStore } from '@/store/ControlStore';
import type { UIProps } from '@/types/UI';
import { Box, type BoxProps } from '@mantine/core';

interface PageProps
  extends UIProps, BoxProps,
  Omit<
    React.ButtonHTMLAttributes<HTMLDivElement>,
    keyof BoxProps
  > {
}

export default function Component({
  children,
  style,
  ignoreBypass=false,
  addTest=[],
  ...props
}: PageProps) {
  const { bypassed } = uesControlStore();

  return (
    <Box
      style={{
        fontWeight: 600,
        fontSize: 'var(--mantine-font-size-sm)',
        color: 'var(--mantine-color-white)',
        opacity: testOpacity([
          bypassed && !ignoreBypass,
          ...addTest
        ]),
        ...style,
      }}
      {...props}
    >
      {children}
    </Box>
  );
}
