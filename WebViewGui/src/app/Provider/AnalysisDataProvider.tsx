import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import AnalysisDataReceiver from '@/ui/AnalysisDataReceiver';
import { useAnimationFrame, useMotionValue } from 'framer-motion';
import { useEffect, useState } from 'react';

export default function App() {
  const { motionValues } = useAnalysisDataStore();
  const value = useMotionValue(0);

  const [isActive, setIsActive] = useState<boolean>(true);
  let dataReceiver: AnalysisDataReceiver | null = null;

  useAnimationFrame((time) => { // (time, delta)
    if (isActive) {
      if (dataReceiver) {
        const data = dataReceiver.getLevels(time);
        if (data) {
          motionValues[0].set(data[0] * 100);
          value.set(data[0] * 100);
        }
      }
    }
  });

  useEffect(() => {
    // eslint-disable-next-line react-hooks/exhaustive-deps
    dataReceiver = new AnalysisDataReceiver(10);
    setIsActive(true);

    return function cleanup() {
      setIsActive(false);
      dataReceiver?.unregister();
    };
  });

  return null;
}
