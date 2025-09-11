'use client';

import { AnalysisDataReceiverLength } from '@/define';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import AnalysisDataReceiver from '@/ui/AnalysisDataReceiver';
import { useAnimationFrame } from 'framer-motion';
import { useEffect, useState } from 'react';

const valuesIdxs = new Array(AnalysisDataReceiverLength).fill(0);

export default function App() {
  const { motionValues, outputNumChannels } = useAnalysisDataStore();
  const [isActive, setIsActive] = useState<boolean>(true);
  let dataReceiver: AnalysisDataReceiver | null = null;

  useAnimationFrame((time) => { // (time, delta)
    if (isActive) {
      if (dataReceiver) {
        outputNumChannels.set(dataReceiver.getOutputNumChannels());

        const data = dataReceiver.getLevels(time);
        if (data) {
          valuesIdxs.map(
            (value, idx) => motionValues[idx].set(data[idx])
          );
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
