import { create } from 'zustand';

interface ActivateState {
  activate: boolean;
  setActivate: (value: boolean) => void;

  trial: number;
  setTrial: (value: number) => void;

  opened: boolean;
  open: () => void;
  close: () => void;
  toggle: () => void;
}

export const useActivateStore = create<ActivateState>((set) => ({
  activate: false,
  setActivate: (value: boolean) => set(() => ({
    activate: value,
  })),

  trial: 0,
  setTrial: (value: number) => set(() => ({
    trial: value,
  })),

  opened: false,
  open: () => set({ opened: true }),
  close: () => set({ opened: false }),
  toggle: () => set((state) => ({ opened: !state.opened })),
}));
