import Stack, { type StackProps } from '@mui/material/Stack';
import { uesControlStore } from '@/store/ControlStore';
import { testOpacity, GlassSx, palette } from '@/define';
import type { PeakMeterProps } from '@/types/PeakMeter';
import Canvas from './Canvas';

interface PeakMeterLedProps extends PeakMeterProps, StackProps {
  length?: number,
}

export default function Page({
  idx,
  sx,
  ignoreBypass = false,
  addTest=[],
  ...props
}: PeakMeterLedProps) {
  const { bypassed } = uesControlStore();

  return (
    <Stack
      spacing={0.7}
      justifyContent="end"
      sx={{
        position: 'relative',
        width: '100%',
        height: '100%',
        flexGrow: 1,
        opacity: testOpacity([
          bypassed && !ignoreBypass,
          ...addTest
        ]),
        backgroundColor: 'var(--mui-palette-secondary-blackest)',
        borderRadius: '0.2em',
        overflow: 'hidden',
        ...GlassSx,
        '& > canvas': {
          position: 'absolute',
          top: 0,
          left: 0,
          width: '100%',
          height: '100%',
          flexGrow:1,
          aspectRatio:'unset'
        },
        ...sx
      }}
      {...props}
    >
      <Canvas
        idx={idx}
        height={100}
        fill={palette.secondary.main}
      />
    </Stack>
  );
}
