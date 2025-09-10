import { create } from 'zustand';

interface ControlState {
  focusAnchor?: HTMLElement | null; // 열기 여부
  setAnchor: (el: HTMLElement | null, open: boolean) => void; // 열기 여부 설정
}

export const uesControlStore = create<ControlState>((set) => ({
  focusAnchor: undefined,
  setAnchor: (el: HTMLElement | null, open: boolean) => set((state) => {
    console.log(el);
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
