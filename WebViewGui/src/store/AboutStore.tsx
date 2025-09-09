import { create } from 'zustand';

interface AboutState {
  open: boolean; // 열기 여부
  setOpen: (value: boolean) => void; // 열기 여부 설정
  handleClose: () => void; // 닫기
}

export const useAboutStore = create<AboutState>((set) => ({
  open: false,
  setOpen: (value: boolean) => set(() => ({
    open: value,
  })),
  handleClose: () => set(() => ({ open: false })),
}));
