import AnalysisDataReceiver from '@/ui/AnalysisDataReceiver';
import Box from '@mui/material/Box';
import { motion, useAnimationFrame, useMotionValue } from 'framer-motion';
import { useEffect, useState } from 'react';

export default function App() {
  const value = useMotionValue(0);

  // const [value, setValue] = useState('');
  const [isActive, setIsActive] = useState<boolean>(true);
  let dataReceiver: AnalysisDataReceiver | null = null;

  useAnimationFrame((time, delta) => {
    if (isActive) {
      if (dataReceiver) {
        const data = dataReceiver.getLevels(time);
        if (data) {
          value.set(data[0] * 100);
        }
      }
    }
  });

  const render = (timeStampMs: number) => {
    if (dataReceiver != null) {
      const levels = dataReceiver.getLevels(timeStampMs);
      if (levels) {
        value.set(levels[0] * 100);
      }
    }
    if (isActive) {
      window.requestAnimationFrame(render);
    }
  };

  useEffect(() => {
    // eslint-disable-next-line react-hooks/exhaustive-deps
    dataReceiver = new AnalysisDataReceiver(10);
    setIsActive(true);
    // window.requestAnimationFrame(render);

    return function cleanup() {
      setIsActive(false);
      dataReceiver?.unregister();
    };
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
