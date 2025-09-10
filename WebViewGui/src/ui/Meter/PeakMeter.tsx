import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import Box from '@mui/material/Box';
import { motion, useAnimationFrame, useMotionValue } from 'framer-motion';

export default function App() {
  const { motionValues } = useAnalysisDataStore();
  const value = useMotionValue(0);

  useAnimationFrame(() => {
    value.set(motionValues[0].get());
  });

  return (
    <Box
      sx={{
        '& .value': {
          position: 'absolute',
          left: 0,
          top: 0,
          width: '100%',
          backgroundColor: '#ff0000'
        }
      }}
    >
      <motion.div
        className="value"
        style={{
          height: value
        }}
      />
    </Box>
  );
}
