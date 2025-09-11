import { create } from 'zustand';

interface ControlState {
  bypassed: boolean,
  setBypass: (value: boolean) => void;

  wetSolo: boolean
  setWetSolo: (value: boolean) => void;

  // 툴팁 포커스 엘리멘트
  focusAnchor?: HTMLElement | null;
  setAnchor: (el: HTMLElement | null, open: boolean) => void;
}

export const uesControlStore = create<ControlState>((set) => ({
  bypassed: false,
  setBypass: (value: boolean) => set(() => ({
    bypassed: value,
  })),

  wetSolo: false,
  setWetSolo: (value: boolean) => set(() => ({
    wetSolo: value,
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
