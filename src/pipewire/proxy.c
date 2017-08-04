/* PipeWire
 * Copyright (C) 2015 Wim Taymans <wim.taymans@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <pipewire/log.h>
#include <pipewire/proxy.h>
#include <pipewire/core.h>
#include <pipewire/remote.h>
#include <pipewire/private.h>

/** \cond */
struct proxy {
	struct pw_proxy this;
};
/** \endcond */

/** Create a proxy object with a given id and type
 *
 * \param proxy another proxy object that serves as a factory
 * \param id Id of the new object, SPA_ID_INVALID will choose a new id
 * \param type Type of the proxy object
 * \return A newly allocated proxy object or NULL on failure
 *
 * This function creates a new proxy object with the supplied id and type. The
 * proxy object will have an id assigned from the client id space.
 *
 * \sa pw_remote
 *
 * \memberof pw_proxy
 */
struct pw_proxy *pw_proxy_new(struct pw_proxy *proxy,
			      uint32_t type,
			      size_t user_data_size)
{
	struct proxy *impl;
	struct pw_proxy *this;
	struct pw_remote *remote = proxy->remote;

	impl = calloc(1, sizeof(struct proxy) + user_data_size);
	if (impl == NULL)
		return NULL;

	this = &impl->this;
	this->remote = remote;

	pw_callback_init(&this->callback_list);
	pw_callback_init(&this->listener_list);

	this->id = pw_map_insert_new(&remote->objects, this);

	if (user_data_size > 0)
		this->user_data = SPA_MEMBER(impl, sizeof(struct proxy), void);

	this->marshal = pw_protocol_get_marshal(remote->conn->protocol, type);

	spa_list_insert(&this->remote->proxy_list, &this->link);

	pw_log_debug("proxy %p: new %u, remote %p, marshal %p", this, this->id, remote, this->marshal);

	return this;
}

void *pw_proxy_get_user_data(struct pw_proxy *proxy)
{
	return proxy->user_data;
}

uint32_t pw_proxy_get_id(struct pw_proxy *proxy)
{
	return proxy->id;
}

void pw_proxy_add_callbacks(struct pw_proxy *proxy,
			    struct pw_callback_info *info,
			    const struct pw_proxy_callbacks *callbacks,
			    void *data)
{
	pw_callback_add(&proxy->callback_list, info, callbacks, data);
}

void pw_proxy_add_listener(struct pw_proxy *proxy,
			   struct pw_callback_info *info,
			   const void *callbacks,
			   void *data)
{
	pw_callback_add(&proxy->listener_list, info, callbacks, data);
}

/** Destroy a proxy object
 *
 * \param proxy Proxy object to destroy
 *
 * \note This is normally called by \ref pw_remote when the server
 *       decides to destroy the server side object
 * \memberof pw_proxy
 */
void pw_proxy_destroy(struct pw_proxy *proxy)
{
	struct proxy *impl = SPA_CONTAINER_OF(proxy, struct proxy, this);

	pw_log_debug("proxy %p: destroy %u", proxy, proxy->id);
	pw_callback_emit_na(&proxy->callback_list, struct pw_proxy_callbacks, destroy);

	pw_map_remove(&proxy->remote->objects, proxy->id);
	spa_list_remove(&proxy->link);

	free(impl);
}

struct pw_callback_list *pw_proxy_get_listeners(struct pw_proxy *proxy)
{
	return &proxy->listener_list;
}

const void *pw_proxy_get_implementation(struct pw_proxy *proxy)
{
	return proxy->marshal->method_marshal;
}