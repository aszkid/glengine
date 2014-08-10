#pragma once

namespace engine {

class system {

public:

	system();
	virtual ~system();

	virtual void init();
	virtual void update(float dt);

};

}
