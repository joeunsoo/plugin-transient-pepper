import AnalysisDataReceiver from '@/ui/AnalysisDataReceiver';
import { motion, useAnimationFrame, useMotionValue } from 'framer-motion';
import { useState } from 'react';

export default function App() {
  // const value = useMotionValue(0.5);
  const [value,setValue] = useState(0);
  const dataReceiver = new AnalysisDataReceiver(10);

  useAnimationFrame((time, delta) => {
    const data = dataReceiver.getLevels(delta);
    if (data) {
      setValue(data[0] * 100);
      // value.set(data[0] * 100);
    }
  });

  return (
    <div>
      <motion.div
        style={{
          width: '200px',
          backgroundColor: '#ff0000',
          height: value
        }}
      />
    </div>
  );
}
