import Stack, { type StackProps } from '@mui/material/Stack';
import { uesControlStore } from '@/store/ControlStore';
import { testOpacity, GlassSx } from '@/define';
import type { PeakMeterProps } from '@/types/PeakMeter';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import { motion, useAnimationFrame, useMotionValue, useTransform } from 'framer-motion';
import applySkew from '@/utils/applySkew';

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

  const { motionValues } = useAnalysisDataStore();
  const value = useMotionValue(0);
  const skewValue = useTransform(value, (value) => applySkew(value, 0.0, 1.0, 0.15));
  const scaleValue = useTransform(skewValue, [0.0, 1.0], [0, 100]);
  const height = useTransform(scaleValue, (value) => `${value}%`);

  useAnimationFrame(() => {
    value.set(motionValues[idx].get());
  });

  return (
    <Stack
      spacing={0.7}
      justifyContent="end"
      sx={{
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
        '& .value': {
          width: '100%',
          backgroundColor: 'var(--mui-palette-secondary-main)',

        },
        ...sx
      }}
      {...props}
    >
      <motion.div
        className="value"
        style={{
          height: height
        }}
      />
    </Stack>
  );
}
