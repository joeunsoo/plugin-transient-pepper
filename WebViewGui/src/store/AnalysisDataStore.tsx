import { create } from 'zustand';
import { MotionValue } from 'framer-motion';

interface AnalysisDataState {
  motionValues: MotionValue<number>[];
}

export const useAnalysisDataStore = create<AnalysisDataState>(() => ({
  motionValues: new Array(16).fill(new MotionValue(0)),
}));
