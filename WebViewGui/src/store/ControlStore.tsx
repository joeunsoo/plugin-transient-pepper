import { create } from 'zustand';

interface ControlState {
  bypassed: boolean,
  setBypass: (value: boolean) => void;

  sidechainListen: boolean,
  setSidechainListen: (value: boolean) => void;

  threshold: number,
  setThreshold: (value: number) => void;

  outputNumChannels: number,
  setOutputNumChannels: (value: number) => void;

  // 툴팁 포커스 엘리멘트
  focusAnchor?: HTMLElement | null;
  setAnchor: (el: HTMLElement | null, open: boolean) => void;
}

export const uesControlStore = create<ControlState>((set) => ({
  bypassed: false,
  setBypass: (value: boolean) => set(() => ({
    bypassed: value,
  })),

  sidechainListen: false,
  setSidechainListen: (value: boolean) => set(() => ({
    sidechainListen: value,
  })),

  threshold: 0,
  setThreshold: (value: number) => set(() => ({
    threshold: value,
  })),

  outputNumChannels: 0,
  setOutputNumChannels: (value: number) => set(() => ({
    outputNumChannels: value,
  })),

  focusAnchor: undefined,
  setAnchor: (el: HTMLElement | null, open: boolean) => set((state) => {
    if (open) {
      if (!state.focusAnchor) {
        return { focusAnchor: el };
      }

      return {};
    } else {
      if (el === state.focusAnchor) {
        return { focusAnchor: null };
      }

      return {};
    }
  })
}));
