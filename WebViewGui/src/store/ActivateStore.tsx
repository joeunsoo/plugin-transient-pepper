import { create } from 'zustand';

interface ActivateState {
  activate:boolean;
  setActivate: (value: boolean) => void;

  open: boolean; // 열기 여부
  setOpen: (value: boolean) => void; // 열기 여부 설정
  handleClose: () => void; // 닫기
}

export const useActivateStore = create<ActivateState>((set) => ({
  activate: false,
  setActivate: (value: boolean) => set(() => ({
    activate: value,
  })),

  open: false,
  setOpen: (value: boolean) => set(() => ({
    open: value,
  })),
  handleClose: () => set(() => ({ open: false })),
}));
