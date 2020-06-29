#pragma once
#include "Level.h"
class MultiPlayerLevel final : public Level
{
public:
    MultiPlayerLevel(size_t, size_t);
    void FetchBoxes() override;
    void FetchTargets() override;
    uint8_t GetNumberOfRemainingHints() override;
    bool CanTakeHint() override;
    void SetRemotePlayer(const std::shared_ptr<Player>&);
    [[nodiscard]] std::shared_ptr<Player> GetRemotePlayer() const;
    void MoveRemotePlayer(MoveDirection);
    void MoveRemotePlayer(const MatrixPosition&);
    void MoveRemoteBox(const std::shared_ptr<Box>&, const MatrixPosition&);

private:
    MoveDirection GetMoveDirection(const MatrixPosition&, const MatrixPosition&);

private:
    std::shared_ptr<Player> m_remotePlayer;
    std::vector<std::shared_ptr<Box>> m_remoteBoxes;
    std::vector<std::shared_ptr<Target>> m_remoteTargets;
};

