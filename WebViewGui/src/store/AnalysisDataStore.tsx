import { create } from 'zustand';

interface AnalysisDataState {
  refreshCount: number;
  refresh: () => void;

  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  data: any;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  setData: (value: any, index: number) => void;
}

export const useAnalysisDataStore = create<AnalysisDataState>((set) => ({
  refreshCount: 0,
  refresh: () => set((state) => ({ refreshCount: state.refreshCount + 1 })),

  data: new Array(16).fill(0),
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  setData: (value: any, index: number) => set((state) => {
    state.data[index] = value;

    return { refreshCount: state.refreshCount + 1 };
  }),
}));
