import { create } from 'zustand';

interface AboutState {
  opened: boolean;
  open: () => void;
  close: () => void;
  toggle: () => void;
}

export const useAboutStore = create<AboutState>((set) => ({
  opened: false,
  open: () => set({ opened: true }),
  close: () => set({ opened: false }),
  toggle: () => set((state) => ({ opened: !state.opened })),
}));
