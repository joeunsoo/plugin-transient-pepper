import { meterEndColor, meterStartColor } from '@/define';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import Box, { type BoxProps } from '@mui/material/Box';
import { motion, useAnimationFrame, useMotionValue, useTransform } from 'framer-motion';

interface PageProps extends BoxProps {
  idx: number,
  startLevel: number,
  endLevel: number,
  mix: number
}

export default function Page({
  idx,
  startLevel,
  endLevel,
  mix,
  sx,
  ...props
}: PageProps) {
  const { motionValues } = useAnalysisDataStore();
  const value = useMotionValue(0);
  const scaleValue = useTransform(value, [startLevel, endLevel], [0.1, 1]);

  useAnimationFrame(() => {
    value.set(motionValues[idx].get());
  });

  return (
    <Box
      sx={{
        height: '100%',
        '& .value': {
          width:'100%',
          height: '100%',
          flexGrow: 1,
          backgroundColor: `color-mix(in srgb, ${meterStartColor} ${mix * 100}%, ${meterEndColor} ${(1 - mix) * 100}%)`,
          border:'1px solid var(--mui-palette-primary-darker)',
          borderRadius: '0.2em',
        },
        ...sx
      }}
      {...props}
    >
      <motion.div
        className="value"
        style={{
          opacity: scaleValue
        }}
      />
    </Box>
  );
}
