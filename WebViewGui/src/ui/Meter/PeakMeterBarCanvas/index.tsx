import { uesControlStore } from '@/store/ControlStore';
import { testOpacity, GlassSx, mantineSpace, secondaryMain } from '@/define';
import type { PeakMeterProps } from '@/types/PeakMeter';
import Canvas from './Canvas';
import { rem, Stack, type StackProps } from '@mantine/core';

interface PeakMeterLedProps extends PeakMeterProps, StackProps {
  length?: number,
}

export default function Page({
  idx,
  style,
  ignoreBypass = false,
  addTest = [],
  ...props
}: PeakMeterLedProps) {
  const { bypassed } = uesControlStore();

  return (
    <Stack
      gap={rem(mantineSpace * 0.7)}
      justify="end"
      style={{
        position: 'relative',
        width: '100%',
        height: '100%',
        flexGrow: 1,
        opacity: testOpacity([
          bypassed && !ignoreBypass,
          ...addTest
        ]),
        backgroundColor: 'var(--mantine-color-secondaryDark-9)',
        borderRadius: '0.2em',
        overflow: 'hidden',
        ...style
      }}
      sx={{
        ...GlassSx,
        '& > canvas': {
          position: 'absolute',
          top: 0,
          left: 0,
          width: '100%',
          height: '100%',
          flexGrow: 1,
          aspectRatio: 'unset'
        },
      }}
      {...props}
    >
      <Canvas
        idx={idx}
        height={100}
        fill={secondaryMain}
      />
    </Stack>
  );
}
