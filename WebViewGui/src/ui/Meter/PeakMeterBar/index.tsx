import Stack, { type StackProps } from '@mui/material/Stack';
import { uesControlStore } from '@/store/ControlStore';
import { calcBypassWetOpacity } from '@/define';
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
  ignoreWetSolo = true,
  ...props
}: PeakMeterLedProps) {
  const { bypassed, wetSolo } = uesControlStore();

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
        opacity: calcBypassWetOpacity({ bypassed, wetSolo, ignoreBypass, ignoreWetSolo }),
        backgroundColor: '#000000',
        border: '1px solid var(--mui-palette-primary-darker)',
        overflow: 'hidden',
        '& .value': {
          width: '100%',
          height: '100%',
          backgroundColor: '#ff0000',

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
