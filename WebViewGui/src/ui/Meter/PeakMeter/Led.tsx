import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import Box from '@mui/material/Box';
import { motion, useAnimationFrame, useMotionValue, useTransform } from 'framer-motion';

type PageProps = {
  id: number,
  startLevel: number,
  endLevel: number
}

export default function Page({
  id,
  startLevel,
  endLevel
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
        width:'100%',
        '& .value': {
          width: '1em',
          height: '0.8em',
          backgroundColor: '#FF8F00'
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
