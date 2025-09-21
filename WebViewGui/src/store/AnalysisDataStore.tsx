import { MotionValue } from 'framer-motion';
import { create } from 'zustand';
import { AnalysisDataReceiverLength } from '@/define';

interface AnalysisDataState {
  motionValues: MotionValue<number>[];
  outputNumChannels: MotionValue<number>;
}

export const useAnalysisDataStore = create<AnalysisDataState>(() => ({
  motionValues: Array.from({ length: AnalysisDataReceiverLength }, () => new MotionValue(0)),
  outputNumChannels: new MotionValue(0),
}));
