import { meterEndColor, meterStartColor } from '@/define';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import Box from '@mui/material/Box';
import { motion, useAnimationFrame, useMotionValue, useTransform } from 'framer-motion';

type PageProps = {
  id: number,
  startLevel: number,
  endLevel: number,
  mix: number
}

export default function Page({
  id,
  startLevel,
  endLevel,
  mix,
}: PageProps) {
  const { motionValues } = useAnalysisDataStore();
  const value = useMotionValue(0);
  const scaleValue = useTransform(value, [startLevel, endLevel], [0.1, 1]);

  useAnimationFrame(() => {
    value.set(motionValues[id].get());
  });

  return (
    <Box
      sx={{
        height: '100%',
        '& .value': {
          height: '100%',
          flexGrow: 1,
          backgroundColor: `color-mix(in srgb, ${meterStartColor} ${mix * 100}%, ${meterEndColor} ${(1 - mix) * 100}%)`,
          border:'1px solid var(--mui-palette-primary-darker)'
        }
      }}
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
